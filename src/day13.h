#pragma once

#include "AdventSolution.h"

class CDay13 final : public CAdventSolution {
public:
    explicit CDay13(const fs::path& aInputDir);
    ~CDay13() override = default;

    void solve() override;
};
