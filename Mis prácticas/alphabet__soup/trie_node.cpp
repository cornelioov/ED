/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //TODO
    isKey_ = is_key_state;
    curr_=children.end();
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //TODO
    ret_val = isKey_;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO
    ret_v = (children.find(k) != children.end());
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //TODO
    (children.find(k) != children.end()) ? node=children.at(k) : node=nullptr;
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //TODO
    ret_val =((has(curr_->first)) && curr_ != children.end());
    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //TODO
    node=curr_->second;
    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO
    symbol = ( children.find(curr_->first) )->first;
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //TODO
    isKey_ = new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //TODO
    curr_= children.find(s);
    if(curr_!=children.end())
    {
        found=true;
    }
    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //TODO
    curr_= children.begin();
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //TODO
    curr_++;
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //TODO
    children.insert({k,node});
    find_child(k);
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //TODO
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip
    out << "["<<" ";
    (is_key()) ? out<<"T" : out<<"F";

    for(auto it=children.begin(); it!=children.end(); ++it)
    {
        out << " ";
        out<< std::hex<< (uint16_t)it->first;
        out<< " ";
        it->second->fold(out);
    }
    out <<" "<<"]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO
    std::string token;
    
    in >> token;
    if(token!="[")
    {
        throw std::runtime_error("Wrong input format");
    }

    in >> token;
    if(token=="T")
    {
        node = TrieNode::create(true);
    }
    else if(token=="F")
    {
        node = TrieNode::create(false);
    }
    else
    {
        throw std::runtime_error("Wrong input format");
    }

    while(in >> token && token!="]")
    {
        node->set_child(char(std::stoi(token,nullptr,16)),TrieNode::create(in));
    }
    if(token!="]")
    {
        throw std::runtime_error("Wrong input format");
    }
    //
    return node;
}
