#pragma once

#include "AdventSolution.h"

class CDay10 final : public CAdventSolution {
public:
    explicit CDay10(const fs::path& aInputDir);
    ~CDay10() override = default;

    void solve() override;
};
