#pragma once

#include "AdventSolution.h"

class CDay5 final : public CAdventSolution {
public:
    explicit CDay5(const fs::path& aInputDir);
    ~CDay5() override = default;

    void solve() override;
};
