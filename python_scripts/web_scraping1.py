"""Volume 3: Introduction to BeautifulSoup.
Alexandra Hurst
<Class>
<Date>
"""


# Example HTML string from the lab.
pig_html = """
<html><head><title>Three Little Pigs</title></head>
<body>
<p class="title"><b>The Three Little Pigs</b></p>
<p class="story">Once upon a time, there were three little pigs named
<a href="http://example.com/larry" class="pig" id="link1">Larry,</a>
<a href="http://example.com/mo" class="pig" id="link2">Mo</a>, and
<a href="http://example.com/curly" class="pig" id="link3">Curly.</a>
<p>The three pigs had an odd fascination with experimental construction.</p>
<p>...</p>
</body></html>
"""

from bs4 import BeautifulSoup
import codecs
import re
import pandas as pd
from matplotlib import pyplot as plt

# Problem 1
def prob1():
    """Examine the source code of http://www.example.com. Determine the names
    of the tags in the code and the value of the 'type' attribute associated
    with the 'style' tag.

    Returns:
        (set): A set of strings, each of which is the name of a tag.
        (str): The value of the 'type' attribute in the 'style' tag.
    """
    return {'html', "head", "title", 'meta','h1', 'a',\
    'style','p', 'div', "body",}, "text/css"


# Problem 2
def prob2(code):
    """Return a list of the names of the tags in the given HTML code."""
    #code=codecs(code, "r")
    pig_soup=BeautifulSoup(code, "html.parser")
    pig_soup=pig_soup.find_all(True)
    return [pig.name for pig in pig_soup]

#problem 3
def prob3(filename="example.html"):
    """Read the specified file and load it into BeautifulSoup. Find the only
    <a> tag with a hyperlink and return its text.
    """
    code=codecs.open(filename, "r")
    code=code.read()
    pig_soup=BeautifulSoup(code, "html.parser")
    return pig_soup.a.get_text().strip()


# Problem 4
def prob4(filename="san_diego_weather.html"):
    """Read the specified file and load it into BeautifulSoup. Return a list
    of the following tags:

    1. The tag containing the date 'Thursday, January 1, 2015'.
    2. The tags which contain the links 'Previous Day' and 'Next Day'.
    3. The tag which contains the number associated with the Actual Max
        Temperature.

    Returns:
        (list) A list of bs4.element.Tag objects (NOT text).
    """
    code=codecs.open(filename, "r")
    code=code.read()
    pig_soup=BeautifulSoup(code, "html.parser")
    a=pig_soup.find(string='Thursday, January 1, 2015').parent
    b=pig_soup.find_all(attrs={"class": re.compile(r'(previous|next)-link')})
    c=pig_soup.find(string="59").parent
    return [a]+b+[c]


# Problem 5
def prob5(filename="large_banks_index.html"):
    """Read the specified file and load it into BeautifulSoup. Return a list
    of the tags containing the links to bank data from September 30, 2003 to
    December 31, 2014, where the dates are in reverse chronological order.

    Returns:
        (list): A list of bs4.element.Tag objects (NOT text).
    """
    code=codecs.open(filename, "r")
    code=code.read()
    pig_soup=BeautifulSoup(code, "html.parser")
    a= pig_soup.find_all(string=re.compile(r"[A-Z][a-z]+\ [0-9]+,\ 20(1[0-4]|0[3-9])"))[:-1]
    final=[pig_soup.find(string=i).parent for i in a[0:-1]]
    return final


# Problem 6
def prob6(filename="large_banks_data.html"):
    """Read the specified file and load it into BeautifulSoup. Create a single
    figure with two subplots:

    1. A sorted bar chart of the seven banks with the most domestic branches.
    2. A sorted bar chart of the seven banks with the most foreign branches.

    In the case of a tie, sort the banks alphabetically by name.
    """
    code=codecs.open(filename, "r")
    code=code.read()
    pig_soup=BeautifulSoup(code, "lxml")
    table=pig_soup.find_all('table')[2]
    new_table=pd.DataFrame(columns=range(0,13), index=range(0,1373))
    row_marker=0
    for row in table.find_all('tr'):
        column_marker=0
        columns=row.find_all('td')
        for column in columns:
            new_table.iat[row_marker, column_marker] = column.get_text().replace(',','')
            column_marker+=1
        row_marker+=1
        if row_marker>=1373:
            break
    dom=new_table[[0,9]]
    dom=dom.iloc[1:40]
    dom[[9]]=dom[[9]].astype(int)
    dom=dom.sort_values(9, axis=0, ascending=False)
    dom=dom.iloc[0:7]
    foreign=new_table[[0,10]]
    foreign=foreign.iloc[1:30]
    foreign[[10]]=foreign[[10]].astype(int)
    foreign=foreign.sort_values(10, axis=0, ascending=False)
    foreign=foreign.iloc[0:7]
    plt.subplot(121)
    plt.bar(range(0,7), dom[[9]].values)
    plt.xticks(range(0,7),dom[[0]].values)
    plt.subplot(122)
    plt.bar(range(0,7),foreign[[10]].values)
    plt.xticks(range(0,7),foreign[[0]].values)
    plt.gcf().autofmt_xdate()
    plt.show()
    


"""if __name__ == "__main__":
    #print(prob1())
    #print(prob2(pig_html))
    #print(prob3("example.html"))
    prob6()"""