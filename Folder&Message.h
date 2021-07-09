#ifndef FOLDER_MESSAGE_H
#define FOLDER_MESSAGE_H
#include <string>
#include <set>
class Folder;
class Message
{
    friend class Folder;
    friend void swap(Message &, Message &);

private:
    std::string contents;
    std::set<Folder *> folders;
    void add_to_Folders(const Message &);
    void remove_from_Folders();
    void addFolder(Folder *f) { folders.insert(f); }
    void removeFolder(Folder *f) { folders.erase(f); }
    void move_Folders(Message *);

public:
    explicit Message(const std::string &str = "") : contents(str) {}
    Message(const Message &);
    Message &operator=(const Message &);
    Message &operator=(Message &&);
    Message(Message &&m) : contents(std::move(m.contents))
    {
        move_Folders(&m);
    }
    ~Message();
    void save(Folder &);
    void remove(Folder &);
};
void Message::move_Folders(Message *m)
{
    m->remove_from_Folders();
    this->folders = std::move(m->folders);
    this->add_to_Folders(*this);
    m->folders.clear();
}
void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.removeMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    for (auto f : this->folders)
        f->removeMsg(this);
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

Message &Message::operator=(const Message &m)
{
    remove_from_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
    return *this;
}

Message &Message::operator=(Message &&m)
{
    m.remove_from_Folders();
    this->contents = std::move(m.contents);
    this->move_Folders(&m);
    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

class Folder
{
    friend void swap(Folder &, Folder &);
    friend class Message;

public:
    Folder() = default;
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();

private:
    std::set<Message *> msgs;
    void add_to_Message(const Folder &);
    void remove_from_Message();
    void addMsg(Message *m) { msgs.insert(m); }
    void removeMsg(Message *m) { msgs.erase(m); }
};

void swap(Folder &lhs, Folder &rhs)
{
    using std::swap;
    lhs.remove_from_Message();
    rhs.remove_from_Message();
    swap(lhs.msgs, rhs.msgs);
    lhs.add_to_Message(lhs);
    rhs.add_to_Message(rhs);
}

void Folder::add_to_Message(const Folder &f)
{
    for (auto m : f.msgs)
        m->addFolder(this);
}

void Folder::remove_from_Message()
{
    for (auto m : this->msgs)
        m->removeFolder(this);
}

Folder::Folder(const Folder &f) : msgs(f.msgs)
{
    add_to_Message(f);
}

Folder &Folder::operator=(const Folder &f)
{
    remove_from_Message();
    this->msgs = f.msgs;
    add_to_Message(f);
    return *this;
}

Folder::~Folder()
{
    remove_from_Message();
}
#endif