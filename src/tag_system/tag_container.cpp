#include "tag_container.hpp"
#include <godot_cpp/core/class_db.hpp>

TagContainer::TagContainer()
{
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    set_physics_process(false);
    set_process_unhandled_input(false);
    set_process_unhandled_key_input(false);
}

TagContainer::~TagContainer()
{
}

String TagContainer::normalize_tag(const String& tag) const
{
    String normalized_tag = tag.strip_edges().to_lower();
    return normalized_tag;
}

bool TagContainer::add_tag(const String& tag)
{
    String normalized_tag = normalize_tag(tag);
    if (normalized_tag.is_empty() || tags.has(normalized_tag))
        return false; // Do not add empty tags or duplicates

    tags.push_back(normalized_tag);
    return true;
}

bool TagContainer::remove_tag(const String& tag)
{
    String normalized_tag = normalize_tag(tag);
    if (normalized_tag.is_empty() || !tags.has(normalized_tag))
        return false; // Do not remove empty tags or non-existing tags

    tags.erase(normalized_tag);
    return true;
}

bool TagContainer::has_tag(const String& tag) const
{
    String normalized_tag = normalize_tag(tag);
    if (normalized_tag.is_empty())
        return false;

    return tags.has(normalized_tag);
}

bool TagContainer::has_all_tags(const TypedArray<String>& tags_to_check) const
{
    for (int i = 0; i < tags_to_check.size(); ++i)
    {
        String tag = tags_to_check[i];
        if (!has_tag(tag))
            return false; // If any tag is missing, return false
    }

    return true;
}

bool TagContainer::has_any_tag(const TypedArray<String>& tags_to_check) const
{
    for (int i = 0; i < tags_to_check.size(); ++i)
    {
        String tag = tags_to_check[i];
        if (has_tag(tag))
            return true; // If any tag is found, return true
    }

    return false; // No tags found
}

bool TagContainer::has_tag_or_ancestor(const String& tag) const
{
    String normalized_tag = normalize_tag(tag);

    // Early return for empty tags
    if (normalized_tag.is_empty())
        return false;

    // Check if the exact tag exists first (most common case)
    if (has_tag(normalized_tag))
        return true;

    // Check ancestors by finding dots from right to left using rfind with position
    int search_from = normalized_tag.length() - 1;
    int dot_pos = normalized_tag.rfind(".", search_from);

    while (dot_pos != -1)
    {
        // Check the ancestor tag (from start to dot position)
        String ancestor_tag = normalized_tag.substr(0, dot_pos);
        if (has_tag(ancestor_tag))
            return true;

        // Move search position to before the current dot and find next dot
        search_from = dot_pos - 1;
        dot_pos = normalized_tag.rfind(".", search_from);
    }

    return false;
}

void TagContainer::set_tags(const TypedArray<String>& new_tags)
{
    tags.clear();
    for (int i = 0; i < new_tags.size(); ++i)
    {
        String tag = new_tags[i];
        String normalized_tag = normalize_tag(tag);
        if (!tags.has(normalized_tag))
            tags.push_back(normalized_tag);
    }

    tags.sort();
}

TypedArray<String> TagContainer::get_tags() const
{
    TypedArray<String> result;
    for (int i = 0; i < tags.size(); ++i)
        result.push_back(tags[i]);

    return result;
}

void TagContainer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("normalize_tag", "tag"), &TagContainer::normalize_tag);
    ClassDB::bind_method(D_METHOD("add_tag", "tag"), &TagContainer::add_tag);
    ClassDB::bind_method(D_METHOD("remove_tag", "tag"), &TagContainer::remove_tag);
    ClassDB::bind_method(D_METHOD("has_tag", "tag"), &TagContainer::has_tag);
    ClassDB::bind_method(D_METHOD("has_all_tags", "tags_to_check"), &TagContainer::has_all_tags);
    ClassDB::bind_method(D_METHOD("has_any_tag", "tags_to_check"), &TagContainer::has_any_tag);
    ClassDB::bind_method(D_METHOD("has_tag_or_ancestor", "tag"), &TagContainer::has_tag_or_ancestor);

    ClassDB::bind_method(D_METHOD("set_tags", "new_tags"), &TagContainer::set_tags);
    ClassDB::bind_method(D_METHOD("get_tags"), &TagContainer::get_tags);
    ClassDB::add_property(get_class_static(), PropertyInfo(Variant::Type::ARRAY, "tags", PROPERTY_HINT_TYPE_STRING, "String"), "set_tags", "get_tags");
}
