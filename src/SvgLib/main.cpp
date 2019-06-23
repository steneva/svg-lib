#include<iostream>
#include <string>
#include "Tag.h"
#include "Parser.h"
#include "ScalableVectorGraphic.h"
#include "SvgLoader.h"
#include "FileHelper.h"
#include "Engine.h"

using namespace std;

void print_tags(const xml::Tag& root, int level = 0)
{
	for (auto i = root.children_begin(); i != root.children_end(); ++i)
	{
		const xml::Tag& current_child = *i;
		const string tag_name = current_child.name();
		const string indent = string(level * 2, ' ');
		cout << indent << "<" << tag_name << " ";
		for (auto attribute = current_child.get_attributes().begin();
		     attribute != current_child.get_attributes().end();
		     ++attribute)
		{
			cout << attribute->name << " = \"" << attribute->value << "\"" << " ";
		}

		if (current_child.has_children())
		{
			cout << ">" << endl;
			print_tags(current_child, level + 1);
			cout << indent << "</" << tag_name << ">" << endl;
		}
		else
		{
			cout << "/>" << endl;
		}
	}
}

int main()
{
	/*string path;
	cin >> path;

	const string file_content = FileHelper::read_file_content(path);
	xml::Tag root = xml::Parser::parse(file_content);

	ScalableVectorGraphic svg = SvgLoader::load(root);
	svg.erase(1);
	svg.print(cout);*/

	Engine engine(std::cin, std::cout);
	engine.run();

	return 0;
}
