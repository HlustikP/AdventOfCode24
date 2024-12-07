#pragma once

#include "AdventSolution.h"

class CDay20 final : public CAdventSolution {
public:
    explicit CDay20(const fs::path& aInputDir);
    ~CDay20() override = default;

    void solve() override;
};
