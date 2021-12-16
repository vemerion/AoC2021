#include <iostream>
#include <vector>
#include <limits>

struct Packet {
  uint8_t version, type;
  uint64_t value;
  std::vector<Packet> subpackets;

  uint16_t versionSum() {
    uint16_t sum = version;
    for (Packet& p : subpackets)
      sum += p.versionSum();
    return sum;
  }

  uint64_t getValue() {
    switch (type) {
      case 4:
        return value;
      case 0: {
        uint64_t sum = 0;
        for (Packet& p : subpackets)
          sum += p.getValue();
        return sum;
      }
      case 1: {
        uint64_t prod = 1;
        for (Packet& p : subpackets)
          prod *= p.getValue();
        return prod;
      }
      case 2: {
        uint64_t min = std::numeric_limits<uint64_t>::max();
        for (Packet& p : subpackets) {
          uint64_t value = p.getValue();
          if (value < min)
            min = value;
        }
        return min;
      }
      case 3: {
        uint64_t max = 0;
        for (Packet& p : subpackets) {
          uint64_t value = p.getValue();
          if (value > max)
            max = value;
        }
        return max;
      }
      case 5:
        return subpackets[0].getValue() > subpackets[1].getValue();
      case 6:
        return subpackets[0].getValue() < subpackets[1].getValue();
      case 7:
        return subpackets[0].getValue() == subpackets[1].getValue();
    }
    return 0;
  }
};

static std::string toBinary(std::string hex) {
  std::string binary = "";
  for (char c : hex)
    switch (c) {
      case '0':
        binary += "0000";
        break;
      case '1':
        binary += "0001";
        break;
      case '2':
        binary += "0010";
        break;
      case '3':
        binary += "0011";
        break;
      case '4':
        binary += "0100";
        break;
      case '5':
        binary += "0101";
        break;
      case '6':
        binary += "0110";
        break;
      case '7':
        binary += "0111";
        break;
      case '8':
        binary += "1000";
        break;
      case '9':
        binary += "1001";
        break;
      case 'A':
        binary += "1010";
        break;
      case 'B':
        binary += "1011";
        break;
      case 'C':
        binary += "1100";
        break;
      case 'D':
        binary += "1101";
        break;
      case 'E':
        binary += "1110";
        break;
      case 'F':
        binary += "1111";
        break;
    }
  return binary;
}

static uint16_t parse(Packet& packet, std::string binary, uint16_t index = 0) {

  packet.version = std::stol(binary.substr(index, 3), 0, 2);
  packet.type = std::stol(binary.substr(index + 3, 3), 0, 2);

  index += 6;
  if (packet.type == 4) {
      std::string n = "";
      while (true) {
        n += binary.substr(index + 1, 4);
        if (binary[index] == '0')
          break;
        index += 5;
      }
      index += 5;
      packet.value = std::stol(n, 0, 2);
  } else {
      char lengthType = binary[index++];
      uint16_t length;
      if (lengthType == '0') {
        length = std::stol(binary.substr(index, 15), 0, 2);
        index += 15;
        while (length != 0) {
          Packet subpacket;
          uint16_t i = parse(subpacket, binary, index) - index;
          packet.subpackets.push_back(subpacket);
          index += i;
          length -= i;
        }
      } else {
        length = std::stol(binary.substr(index, 11), 0, 2);
        index += 11;
        for (uint16_t i = 0; i < length; i++) {
          Packet subpacket;
          index = parse(subpacket, binary, index);
          packet.subpackets.push_back(subpacket);
        }
      }
  }
  return index;
}

int main() {
  Packet packet;
  std::string input;
  
  std::cin >> input;
  input = toBinary(input);
  parse(packet, input);

  std::cout << "Part 1 result = " << packet.versionSum() << '\n';
  std::cout << "Part 2 result = " << packet.getValue() << '\n';
  return 0;
}
