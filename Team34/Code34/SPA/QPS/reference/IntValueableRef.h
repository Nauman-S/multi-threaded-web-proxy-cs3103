#pragma once
#include "Ref.h"
#include <optional>
class IntValueableRef :
    public Ref
{
    using Ref::Ref;

public:
    virtual bool IsIntValued();

    virtual std::optional<int> ValueAsInt();
};

