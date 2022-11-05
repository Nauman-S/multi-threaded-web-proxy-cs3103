#pragma once

#include <string>
#include <memory>

#include "ValType.h"
#include "../clause/AttrType.h"
#include "../../Utils/type/RefType.h"
class DataRetriever;


class Ref {
protected:
    ValType val_type_;
    std::string val_;
    AttrType attr_type_;

public:
    Ref(ValType val_type, std::string val, AttrType attr_type)
        : val_type_{ val_type }, val_{ val }, attr_type_{ attr_type } {
    };

    Ref(std::shared_ptr<Ref> ref, AttrType attr_type)
        : val_type_{ ref->GetValType() }, val_{ ref->GetName() }, attr_type_{ attr_type } {
    };

    virtual const std::string& GetName() const { return val_; }

    virtual const ValType GetValType() { return val_type_; }

    virtual const RefType GetRefType() = 0;

    virtual bool IsAttrTypeDefault() = 0;

    virtual AttrType GetDefaultAttrType() = 0;

    virtual const AttrType GetAttrType() { return attr_type_; }

    virtual const void SetAttrType(AttrType attr_type) { attr_type_ = attr_type; }

    virtual std::string GetAttrValue(DataRetriever& data_retriever, std::string& value);

    // Make a copy of an object
    virtual std::shared_ptr<Ref> Clone() = 0;
};

