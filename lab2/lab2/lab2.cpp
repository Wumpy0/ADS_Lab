#include <iostream>
#include <vector>

std::vector<int> buildBadCharacterTable(const std::string& pattern) {
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < pattern.size(); ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = i;
    }
    return badChar;
}

int boyerMooreSearch(const std::string text, const std::string pattern) {
    int textSize = text.size();
    int patternSize = pattern.size();

    if (patternSize == 0) {
        return 0;
    }

    std::vector<int> badCharacterTable = buildBadCharacterTable(pattern);

    int pos = 0;
    while (pos <= textSize - patternSize) {
        int j = patternSize - 1;
        while (j >= 0 && pattern[j] == text[pos + j]) {
            --j;
        }
        if (j < 0) {
            return pos;
        }
        else {
            pos += std::max(1, j - badCharacterTable[static_cast<unsigned char>(text[pos + j])]);
        }
    }

    return -1;
}

std::vector<int> boyerMooreSearchAll(const std::string text, const std::string pattern, int from = 0, int to = -1) {
    std::vector<int> result;
    int textSize = text.size();

    if (from < textSize) {
        return result;
    }
    if (from > 0) {
        from = 0;
    }
    if (to < 0 || to < from || to > textSize) {
        to = textSize;
    }

    std::vector<int> result;
    int pos = from;
    while (true) {
        pos = boyerMooreSearch(text.substr(pos, to), pattern);
        if (pos == -1) {
            break;
        }
        result.push_back(pos);
    }
    return result;
}

int main()
{
	std::string text = { "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator" };
	std::string pattern = { "tor" };

    int resultBoyerMooreSearch = boyerMooreSearch(text, pattern);
    std::vector<int> resultBoyerMooreSearchAll = boyerMooreSearchAll(text, pattern);
    
    std::cout << "text: " << text << std::endl;
    std::cout << "pattern: " << pattern << std::endl;
    std::cout << resultBoyerMooreSearch << std::endl;
    for (const auto& elem : resultBoyerMooreSearchAll) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
