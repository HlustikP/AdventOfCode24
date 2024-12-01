#pragma once

#include "AdventSolution.h"

class CDay1 final : public CAdventSolution {
public:
    explicit CDay1(const fs::path& aInputDir);
    ~CDay1() override = default;

    void solve() override;
};
