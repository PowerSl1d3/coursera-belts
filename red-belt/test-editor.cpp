#include <string>
#include "test_runner.h"
using namespace std;
#include <list>


class Editor
{
public:
	Editor();

	void Left();

	void Right();

	void Insert(char token);

	void Cut(size_t tokens = 1);

	void Copy(size_t tokens = 1);

	void Paste();

	std::string GetText() const;

private:
	std::list<char> text_;
	std::list<char> buffer_;
	std::list<char>::iterator cursor_;

	void Deleter(const std::list<char>::iterator& l);
	void Inserter(const std::list<char>::iterator& l);
	std::list<char>::iterator ComputeCursor(size_t tokens);
};


inline void Editor::Deleter(const std::list<char>::iterator& l)
{
	text_.erase(l, cursor_);
}


inline void Editor::Inserter(const std::list<char>::iterator& l)
{
	buffer_.clear();
	buffer_.insert(buffer_.end(), l, cursor_);
}


inline std::list<char>::iterator Editor::ComputeCursor(size_t tokens)
{
	const size_t dist_to_end = std::distance(cursor_, text_.end());
	const auto tmp_iter = cursor_;
	tokens >= dist_to_end ? cursor_ = text_.end() : cursor_ = std::next(cursor_, tokens);

	return tmp_iter;
}


inline Editor::Editor()
{
	cursor_ = text_.begin();
}


inline void Editor::Left()
{
    if (cursor_ != text_.begin())
    {
		cursor_ = std::prev(cursor_);
    }
}


inline void Editor::Right()
{
    if (cursor_ != text_.end())
    {
		cursor_ = std::next(cursor_);
    }
}


inline void Editor::Insert(char token)
{
	text_.insert(cursor_, token);
}


inline void Editor::Cut(size_t tokens)
{
	const auto tmp_iter = ComputeCursor(tokens);

	Inserter(tmp_iter);
	Deleter(tmp_iter);
}


inline void Editor::Copy(size_t tokens)
{
	const auto tmp_iter = ComputeCursor(tokens);
	Inserter(tmp_iter);
}


inline void Editor::Paste()
{
    if (!buffer_.empty())
    {
		text_.insert(cursor_, buffer_.begin(), buffer_.end());
    }
}


inline std::string Editor::GetText() const
{
	return std::string(text_.begin(), text_.end());
}

/*class Editor {
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
    : cursor(text.end())
  {}
  void Left() {
    if (cursor > text.begin()) {
      cursor--;
    }
  }
  void Right() {
    if (cursor < text.end()) {
      cursor++;
    }
  }
  void Insert(char token) {
    text.insert(cursor++, token);
  }
  void Cut(size_t tokens = 1) {
    if (tokens == 0) {
      buffer.clear();
      return;
    }
    if (cursor + tokens < text.end()) {
      buffer = {cursor, cursor + tokens};
      text.erase(cursor, cursor + tokens);
    } else {
      buffer = {cursor, text.end()};
      text = {text.begin(), cursor};
    }
  }
  void Copy(size_t tokens = 1) {
    if (tokens == 0) {
      buffer.clear();
      return;
    }
    if (cursor + tokens < text.end()) {
      buffer = {cursor, cursor + tokens};
    } else {
      buffer = {cursor, text.end()};
    }
  }
  void Paste() {
    text.insert(cursor, buffer.begin(), buffer.end());
    cursor += buffer.size();
  }
  string GetText() const {
    return text;
  }
private:
  std::string text;
  std::string buffer;
  std::string::iterator cursor;
};*/

/*class Editor {
  public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor()
  : cursor(text.size())
  {}
  void Left() {
  if (cursor > 0) {
  cursor--;
  }
  }
  void Right() {
  if (cursor < text.size()) {
  cursor++;
  }
  }
  void Insert(char token) {
  text.insert(cursor++, string(1,token));
  }
  void Cut(size_t tokens = 1) {
  if (tokens == 0) {
  buffer.clear();
  return;
  }
  if (cursor + tokens < text.size()) {
  buffer = text.substr(cursor, tokens);
  text = text.substr(0, cursor) + text.substr(cursor + tokens, text.size() - cursor - tokens + 1);
  } else {
  buffer = text.substr(cursor, text.size() - cursor);
  text = text.substr(0, cursor);
  }
  }
  void Copy(size_t tokens = 1) {
  if (tokens == 0) {
  buffer.clear();
  return;
  }
  if (cursor + tokens < text.size()) {
  buffer = text.substr(cursor, tokens);
  } else {
  buffer = text.substr(cursor, text.size() - cursor - tokens + 1);
  }
  }
  void Paste() {
  text.insert(cursor, buffer);
  cursor += buffer.size();
  }
  string GetText() const {
  return text;
  }
  private:
  std::string text;
  std::string buffer;
  size_t cursor;
  };*/

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

void TestCopyPasteLastChars()
{
  Editor editor;
  TypeText(editor, "happy birthday");
  editor.Left();
  editor.Left();
  editor.Copy(5);
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}

void TestCut()
{
  Editor editor;
  //1
  editor.Cut(10);
  editor.Insert('a');
  editor.Left();
  //2
  editor.Cut(1);
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "a");
  //3
  editor.Cut(0);
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "a");
  TypeText(editor, "bcde");
  editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
  //4
  editor.Cut(10);
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "abcde");
  editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
  //5
  editor.Cut(5);
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Paste();
  //6
  editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
  editor.Cut(1);
  ASSERT_EQUAL(editor.GetText(), "bcde");
  editor.Right();
  editor.Cut(1);
  ASSERT_EQUAL(editor.GetText(), "bde");
  editor.Cut(1);
  editor.Cut(1);
  ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
  Editor editor;
  //1
  editor.Copy(10);
  editor.Insert('a');
  editor.Paste();
  editor.Left();
  ASSERT_EQUAL(editor.GetText(), "a");
  //2
  editor.Copy(1);
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "aa");//between a
  //3
  editor.Copy(0);
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "aa");
  TypeText(editor, "bcde");
  editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
  //4
  editor.Cut(10);
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "abcdea");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestCopyPasteLastChars);
  RUN_TEST(tr, TestCut);
  RUN_TEST(tr, TestCopy);
  return 0;
}
