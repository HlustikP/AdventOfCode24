#pragma once

#include "AdventSolution.h"

class CDay21 final : public CAdventSolution {
public:
    explicit CDay21(const fs::path& aInputDir);
    ~CDay21() override = default;

    void solve() override;
};
