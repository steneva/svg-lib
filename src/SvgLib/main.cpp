#include<iostream>
#include <string>
#include "Tag.h"
#include "Parser.h"
#include "ScalableVectorGraphic.h"
#include "SvgLoader.h"
#include "FileReader.h"

using namespace std;

void print_tags(const xml::Tag& root, int level = 0)
{
	for (auto i = root.children_begin(); i != root.children_end(); ++i)
	{
		const xml::Tag& current_child = *i;
		const string tag_na = current_child.name();
		const string indent = string(level * 2, ' ');
		cout << indent << "<" << tag_na << " ";
		for (auto attribute = current_child.get_attributes().begin();
		     attribute != current_child.get_attributes().end();
		     ++attribute)
		{
			cout << attribute->first << " = \"" << attribute->second << "\"" << " ";
		}

		if (current_child.has_children())
		{
			cout << ">" << endl;
			print_tags(current_child, level + 1);
			cout << indent << "</" << tag_na << ">" << endl;
		}
		else
		{
			cout << "/>" << endl;
		}
	}
}

int main()
{
	string path;
	cin >> path;

	const string file_content = FileReader::get_file_content(path);
	xml::Tag root = xml::Parser::parse(file_content);

	ScalableVectorGraphic svg = SvgLoader::load(root);
	svg.erase(1);
	svg.print(cout);

	return 0;
}
