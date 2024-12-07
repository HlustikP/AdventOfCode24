#pragma once

#include "AdventSolution.h"

class CDay18 final : public CAdventSolution {
public:
    explicit CDay18(const fs::path& aInputDir);
    ~CDay18() override = default;

    void solve() override;
};
