#pragma once

#include "AdventSolution.h"

class CDay23 final : public CAdventSolution {
public:
    explicit CDay23(const fs::path& aInputDir);
    ~CDay23() override = default;

    void solve() override;
};
