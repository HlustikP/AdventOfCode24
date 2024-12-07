#pragma once

#include "AdventSolution.h"

class CDay14 final : public CAdventSolution {
public:
    explicit CDay14(const fs::path& aInputDir);
    ~CDay14() override = default;

    void solve() override;
};
