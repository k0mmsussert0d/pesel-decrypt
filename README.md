# pesel-decrypt

Simple one-file C++ application extracting data from given PESEL number.
<b>PESELM</b> ( <i>pol.</i> Powszechny Elektroniczny System Ewidencji Ludności, Universal Electronic System for Registration of the Population) is a Polish national identification number, used in Poland since 1979.

PESEL number contains:
<ul>
<li>date of birth,</li>
<li>gender,</li>
<li>validity digit,</li>
<li>serial number</li>.
</ul>

For specific information about algorithms used to put data into a 11-digits-long string, please reffer to <a href="https://en.wikipedia.org/wiki/PESEL">Wikipedia</a>.

PESEL number is the main method of citizens identification. Each record in the database contains of 26 fields (additional 7 for foreigners) and it is assigned to every new Polish inhabitant.
