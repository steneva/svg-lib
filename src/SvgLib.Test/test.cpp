#include "pch.h"
#include "../SvgLib/FileHelper.h"
#include "../SvgLib/Parser.h"
#include "../SvgLib/SvgLoader.h"
#include <filesystem>

TEST(XmlParseTest, NoChanges_PreservesOriginalFile)
{
	const auto content = FileHelper::read_file_content("..\\Samples\\caution.svg");
	auto root = xml::Parser::parse(content);
	std::stringstream output;
	root.to_xml(output);

	EXPECT_EQ(content, output.str());
}

class AttributeCollectionTest : public testing::Test
{
private:
	xml::Tag* _root = nullptr;
	ScalableVectorGraphic _svg = nullptr;
protected:
	void SetUp() override
	{
		const auto content = FileHelper::read_file_content("..\\Samples\\caution.svg");
		this->_root = new xml::Tag(xml::Parser::parse(content));
		this->_svg = SvgLoader::load(*_root);
	}

	void TearDown() override
	{
		delete _root;
	}

public:
	xml::Tag root() const
	{
		return *_root;
	}
};

TEST_F(AttributeCollectionTest, AttributeAdd_Reflected)
{
	const std::string attribute_name = "pesho";
	const std::string attribute_value = "gosho";

	xml::Tag tag = *(root().children_begin());
	tag.attributes().set(attribute_name, attribute_value);

	const std::string attribute_new_value = tag.attributes().get(attribute_name);

	EXPECT_EQ(attribute_value, attribute_new_value);
}

TEST_F(AttributeCollectionTest, AttributeChange_Reflected)
{
	auto tag = *(root().children_begin());
	const Attribute original = *(tag.attributes().begin());

	std::string attribute_new_value = "new-value";
	tag.attributes().set(original.name, attribute_new_value);

	const std::string attribute_current_value = tag.attributes().get(original.name);

	EXPECT_EQ(attribute_new_value, attribute_current_value);
}

TEST_F(AttributeCollectionTest, CreateRectangle)
{
}
