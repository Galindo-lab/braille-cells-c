

# Sistema De Lectoescritura Braille

Para escribir en braille se utilizan seis puntos para
representar los símbolos del alfabeto, los números y 
caracteres de control.

Cada carácter esta compuesto de seis puntos, para poder
especificar los relieves del carácter usualmente se utiliza 
siguiente nomenclatura:

    1 4
    2 5
    3 6


# Representar Los Caracteres

Además de la forma con relieves o visual podemos representar 
los caracteres mediante los números de sus relieves, ejemplo:


## Carácter J:

    . o     
    o o --> 245
    . .


## Carácter R:

    o .     
    o o --> 1235
    o .


<a id="org1104c8c"></a>

# Sistema De Braillecells

Podemos representar los relieves del carácter mediante el 
sistema binario, de manera que el bit menos significativo 
represente el relieve con la posición mas baja:

-   el relieve 1 es el bit 0
-   el relieve 2 es el bit 1
-   el relieve 3 es el bit 2
-   etc&#x2026;

    1 4       0 3
    2 5  -->  1 4
    3 6       2 5

Entonces en memoria los caracteres se verían representados 
de la siguiente manera:

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-right" />

<col  class="org-right" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Carácter</th>
<th scope="col" class="org-right">Braille</th>
<th scope="col" class="org-right">BrailleCell</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">a</td>
<td class="org-right">1</td>
<td class="org-right">000001</td>
</tr>


<tr>
<td class="org-left">b</td>
<td class="org-right">12</td>
<td class="org-right">000011</td>
</tr>


<tr>
<td class="org-left">j</td>
<td class="org-right">245</td>
<td class="org-right">011010</td>
</tr>


<tr>
<td class="org-left">r</td>
<td class="org-right">1235</td>
<td class="org-right">010111</td>
</tr>
</tbody>
</table>


# Extraer Los Relieves Del Carácter

Para conocer el estado de cada relieve solo basta con crear una
mascara con la posición del relieve que nos interesa conocer, 
cabe recordar que [los relieves empiezan desde la posición cero](#org1104c8c):

    char get_dot(BrailleCell character, char dot_pos) {
      return (character.dots & 1 << dot_pos);
    }

