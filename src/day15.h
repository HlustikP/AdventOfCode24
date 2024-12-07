#pragma once

#include "AdventSolution.h"

class CDay15 final : public CAdventSolution {
public:
    explicit CDay15(const fs::path& aInputDir);
    ~CDay15() override = default;

    void solve() override;
};
