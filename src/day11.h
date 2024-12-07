#pragma once

#include "AdventSolution.h"

class CDay11 final : public CAdventSolution {
public:
    explicit CDay11(const fs::path& aInputDir);
    ~CDay11() override = default;

    void solve() override;
};
