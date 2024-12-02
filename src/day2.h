#pragma once

#include "AdventSolution.h"

class CDay2 final : public CAdventSolution {
public:
    explicit CDay2(const fs::path& aInputDir);
    ~CDay2() override = default;

    void solve() override;
};
