#include "pch.h"
#include "../SvgLib/FileHelper.h"
#include "../SvgLib/Parser.h"
#include "../SvgLib/SvgLoader.h"
#include <filesystem>

TEST(TestCaseName, TestName) {
	std::cout<< std::filesystem::current_path()<< std::endl;
	auto path = std::filesystem::current_path().append("");
	std::cout<<path.string()<< std::endl;
	const auto content = FileHelper::read_file_content("..\\Samples\\caution.svg");
	auto root = xml::Parser::parse(content);
	std::stringstream output;
	root.to_xml(output);

	EXPECT_EQ(content, output.str());
}

