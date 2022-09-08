#pragma once

#include <optional>

#include "Ref.h"


class IntValueableRef :
    public Ref
{
    using Ref::Ref;

public:
    virtual bool IsIntValued();

    virtual std::optional<int> ValueAsInt();
};

