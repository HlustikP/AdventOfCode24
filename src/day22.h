#pragma once

#include "AdventSolution.h"

class CDay22 final : public CAdventSolution {
public:
    explicit CDay22(const fs::path& aInputDir);
    ~CDay22() override = default;

    void solve() override;
};
