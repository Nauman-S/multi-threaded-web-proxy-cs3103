#pragma once

#include <memory>
#include <optional>
#include <string>

#include "Ref.h"

class RefFactory
{
public:
	static const std::string str1;
	std::optional<std::shared_ptr<Ref>> RefFactory::CreateReference(std::string design_entity_, std::string synonym_);
};

const std::string str1 = "Bob";

