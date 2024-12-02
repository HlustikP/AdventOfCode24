#pragma once

#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class CAdventSolution {
public:
    CAdventSolution(const fs::path& aInputDir, const std::string& aHeadline) : mHeadline{ aHeadline }, mInputDir{ aInputDir } {};
    virtual ~CAdventSolution() = default;
    CAdventSolution(const CAdventSolution&) = delete;
    CAdventSolution& operator=(const CAdventSolution&) = delete;
    CAdventSolution(CAdventSolution&&) = default;
    CAdventSolution& operator=(CAdventSolution&&) = default;

    void printHeadline() const {
        std::cout << '\n' << mHeadline << std::endl;
    }

    void printTime() const {
        const auto lTimeMicroSeconds = std::chrono::duration_cast<std::chrono::microseconds>(mEnd - mStart).count();
        if (lTimeMicroSeconds < 10'000)
        {
            std::cout << "Time: " << lTimeMicroSeconds << "us" << std::endl;
        }
        else
        {
            std::cout << "Time: " << lTimeMicroSeconds / 1000 << "ms" << std::endl;
        }
    }

    virtual void solve() = 0;

    std::optional<std::string> loadFile(const std::string& aInputFile) const
    {
        if (!fs::exists(mInputDir)) {
            std::cerr << "[ERROR] [FILE] Input Directory '" << mInputDir << "' does not exist" << std::endl;
            return std::nullopt;
        }

        const auto lFullPath = mInputDir / aInputFile;

        if (!fs::exists(lFullPath)) {
            std::cerr << "[ERROR] [FILE] File '" << lFullPath << "' does not exist" << std::endl;
            return std::nullopt;
        }

        try {
            std::ifstream lIfstream(lFullPath, std::ios::in | std::ios::binary);
            const auto lSize = fs::file_size(lFullPath);
            std::string lResult(lSize, '\0');
            lIfstream.read(lResult.data(), static_cast<std::streamsize>(lSize));

            return lResult;
        }
        catch (const std::exception& e) {
            std::cerr << "[ERROR] [FILE] " << e.what() << std::endl;
            return std::nullopt;
        }
    }

protected:
    std::string mHeadline{};
    fs::path mInputDir{};
    std::chrono::high_resolution_clock::time_point mStart{};
    std::chrono::high_resolution_clock::time_point mEnd{};
};
