# B-Tree
B-Tree implementation for Files' Organization project

## Project Division
---------------------------------------------------------------------------
## File Structuring
---------------------------------------------------------------------------
### Field types: 

- **Fixed-size:** ticket, documento, dataHoraCadastro, dataHoraAtualiza

- **Varied-size:** dominio, nome, cidade, uf

**Fixed fields come all together on the beginning of the record**,
followed by the variable fields.

Variable fields should have **size indicators** before them. Fixed fields 
do not need any type of indicators, they are always there. Records
should have **delimiters** at the end of them.

---------------------------------------------------------------------------
## FAQ

**Q: My question isn't answered here, what now?**

- A: Check the slides. Seriously, check it 100 times.



**Q: Checked 100 times, what now?!?!**

- A: Check 1000 times.



**Q: My PC exploded cuz I checked the slides too much.**

- A: Let's ask the teacher or her intern.



**Q: Should I put the fields with fixed size together?**

- A: Yes. Put them at the beginning of the record.



**Q: But all the files have fixed number of fields.**

- A: Yea we know, just "pretend" they have not unless it is 
'fixed number of fields' and we'll get 10...
