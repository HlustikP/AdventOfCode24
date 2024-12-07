#pragma once

#include "AdventSolution.h"

class CDay7 final : public CAdventSolution {
public:
    explicit CDay7(const fs::path& aInputDir);
    ~CDay7() override = default;

    void solve() override;
};
