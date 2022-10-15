#pragma once

#include <string>

#include "ValType.h"
#include "../../Utils/type/RefType.h"
#include "../AttrType.h"

class DataRetriever;

class Ref {
protected:
    ValType val_type_;
    std::string val_;
    AttrType attr_type_;

public:
    Ref(ValType val_type, std::string val, AttrType attr_type)
        : val_type_{ val_type }, val_{ val }, attr_type_{attr_type} {
    };

    virtual const std::string& GetName() const { return val_; }

    virtual const ValType GetValType() { return val_type_; }

    virtual const RefType GetRefType() = 0;

    virtual bool IsAttrTypeDefault() = 0;

    virtual AttrType GetDefaultAttrType() = 0;

    virtual std::string GetAttrValue(DataRetriever& data_retriever, std::string& value);
};

