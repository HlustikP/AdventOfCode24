#pragma once

#include "AdventSolution.h"

class CDay25 final : public CAdventSolution {
public:
    explicit CDay25(const fs::path& aInputDir);
    ~CDay25() override = default;

    void solve() override;
};
