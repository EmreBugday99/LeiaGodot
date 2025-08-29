#ifndef TAG_CONTAINER_HPP
#define TAG_CONTAINER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class TagContainer : public Node
{
    GDCLASS(TagContainer, Node);

private:
    TypedArray<String> tags;

public:
    TagContainer();
    ~TagContainer();

    String normalize_tag(const String& tag) const;
    bool add_tag(const String& tag);
    bool remove_tag(const String& tag);
    bool has_tag(const String& tag) const;
    bool has_all_tags(const TypedArray<String>& tags_to_check) const;
    bool has_any_tag(const TypedArray<String>& tags_to_check) const;
    bool has_tag_or_ancestor(const String& tag) const;

    void set_tags(const TypedArray<String>& new_tags);
    TypedArray<String> get_tags() const;

protected:
    static void _bind_methods();
};

#endif // TAG_CONTAINER_HPP