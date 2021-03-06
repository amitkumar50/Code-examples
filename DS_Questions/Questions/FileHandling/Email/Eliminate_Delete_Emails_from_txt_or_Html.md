## Problem
- Remove all email addresses from file
```html
<HTML>
<HEAD>
<TITLE>Your Title Here</TITLE>
</HEAD>
<BODY BGCOLOR="FFFFFF">
<CENTER><IMG SRC="clouds.jpg" ALIGN="BOTTOM"> </CENTER>
<HR>
<a href="http://somegreatsite.fb.test.com">Link Name</a>is a link to another nifty site
<H1>This is a Header</H1>
<H2>This is a Medium Header</H2>
Send me mail at <a href="mailto:Email">support@fb.com</a>.

<P> Website: test.fb.test.com and then go to test1.fb.test.org
<P> <B>This is a new paragraph!</B>
<BR> <B><I>This is a new sentence without a paragraph break, in bold italics.</I></B>
<HR>
</BODY>
</HTML>
```

## C++
- **Logic:** Read input.html file word by word. keep dumping words into temporary file. Skip email to be dumped into temporary. Rename
  - *1.* Open input.html file ifstream and temporary with ofstream. ie with [input stream & output streams](https://github.com/amitkumar50/Code-examples/tree/master/Languages/programming_lang/c%2B%2B/Streams) respectively.
  - *2.* Read every line from input file, Tokenize the line for words.
- **Complexity**
  - **Time:** O(n+m). n:Non-Emails, m:Emails
  - **Space:** O(n)
- **Code**
  - [getline](https://github.com/amitkumar50/Code-examples/tree/master/Languages/programming_lang/c++/Utility-Library/Strings/Functions), 
```c++
#include<iostream>
#include<fstream>
#include<sstream>

int main(){
  std::ifstream fin("input.html");      //1
  std::ofstream fout("temporary");

  std::string strLine, strWord;

  while (fin) {
    std::getline(fin, strLine);
    std::stringstream oSS(strLine);
    //Tokenize the line to read the word
    while (std::getline(oSS, strWord, ' ')){
      std::cout<<strWord<<" ";
      if (strWord.find('@') == std::string::npos)
        fout << strWord;
    }
    fout <<std::endl;
  }
  fin.close();
  fout.close();
}
```

## Python
- **Logic:** Read words from input file(skip email), Write words to output file. rename output file.
  - *0.* [Import re, os modules](https://github.com/amitkumar50/Code-examples/tree/master/Languages/programming_lang/python/Modules)
  - *1.* Open output file `fout` in write mode.
  - *2.* Open input file in `f` in read mode and read every line
  - *3.* Create [list](https://github.com/amitkumar50/Code-examples/tree/master/Languages/programming_lang/python/containers) of email addresses from line using [re module](https://github.com/amitkumar50/Code-examples/tree/master/Languages/programming_lang/python/Modules/Re_RegularExpression)
    - Example lst = `['a@test.com', 'b@test.com']`
  - *4.* if word is not in list. Write into file
  - *5.* close both inupt, out files
  - *6.* Rename newly created file to old
- **Complexity**
  - **Time:** n:words in input file. m:Emails in input file. O(mn)
  - **Space:** O(n+m): Creating a new file
- **Code**
```python
import re
import os
fout = open("html-file-new.html", "w")

with open("html-file.html", "r") as f: 
  for line in f:
    lst = re.findall('\S+@\S+',line)
    for word in line.split():
      if word not in lst:
        fout.write(word)
    fout.write("\r\n")
f.close()
fout.close()        
os.rename("html-file-new.html","html-file.html")
```
