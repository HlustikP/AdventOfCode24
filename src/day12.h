#pragma once

#include "AdventSolution.h"

class CDay12 final : public CAdventSolution {
public:
    explicit CDay12(const fs::path& aInputDir);
    ~CDay12() override = default;

    void solve() override;
};
