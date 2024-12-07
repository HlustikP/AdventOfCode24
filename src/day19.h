#pragma once

#include "AdventSolution.h"

class CDay19 final : public CAdventSolution {
public:
    explicit CDay19(const fs::path& aInputDir);
    ~CDay19() override = default;

    void solve() override;
};
