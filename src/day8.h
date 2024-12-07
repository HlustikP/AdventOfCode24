#pragma once

#include "AdventSolution.h"

class CDay8 final : public CAdventSolution {
public:
    explicit CDay8(const fs::path& aInputDir);
    ~CDay8() override = default;

    void solve() override;
};
