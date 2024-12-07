#pragma once

#include "AdventSolution.h"

class CDay16 final : public CAdventSolution {
public:
    explicit CDay16(const fs::path& aInputDir);
    ~CDay16() override = default;

    void solve() override;
};
