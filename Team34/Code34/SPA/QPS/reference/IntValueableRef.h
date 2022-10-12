#pragma once

#include <optional>

#include "Ref.h"


class IntValueableRef : public Ref {
public:
    using Ref::Ref;

    virtual bool IsIntValued();

    virtual std::optional<int> ValueAsInt();
};

