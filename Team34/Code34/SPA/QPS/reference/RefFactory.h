#pragma once

#include <memory>
#include <optional>
#include <string>

#include "Ref.h"

class RefFactory
{
public:
	std::optional<std::shared_ptr<Ref>> RefFactory::CreateReference(std::string design_entity_, std::string synonym_);
};


