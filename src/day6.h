#pragma once

#include "AdventSolution.h"

class CDay6 final : public CAdventSolution {
public:
    explicit CDay6(const fs::path& aInputDir);
    ~CDay6() override = default;

    void solve() override;
};
