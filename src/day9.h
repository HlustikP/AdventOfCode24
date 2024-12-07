#pragma once

#include "AdventSolution.h"

class CDay9 final : public CAdventSolution {
public:
    explicit CDay9(const fs::path& aInputDir);
    ~CDay9() override = default;

    void solve() override;
};
