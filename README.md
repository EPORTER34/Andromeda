# Andromeda
3d simulator for a satellite network the plots satellite orbits & simulates communications between the ground and sattelites
will contain a preset of a LEO, MEO, & GEO sat network & the option to custom load a network <br>
Assumptions: <br>
circular satellite orbits <br>
multipath mostly negligeble <br>
ignoring drag & any other orbital drift <br>
assuming earth is a sphere of radius 6378 km <br>
for atmospheric gas absorption, the mean annual global atmosphere is used, as detailed in ITU-R P.835 <br>
the attenuation from mean annual global is then approximated with the formula y_surf * L_eff / sin(theta) <br>

todo: <br>
backend: <br>
  -sat obrital mechanics <br>
    -tle parsing <br>
    -sgp4 propogation <br>
  -ground to sat comm <br>
    -link budget analysis <br>
    -path loss/SNR <br>
    -shadowing & atmospheric effects <br>
  -link everything together <br>
<br>

frontend: <br>
  viewing pannels <br>
    satellite numbers (with dropdown for orbital elements?) <br>
    doppler effect <br>
    link budget (with dropdowns for losses) <br>

<br>
  potentially add multithreading <br>
<br>
readme<br>
  actually document (assumptions made, features, design decisions) <br>


Losses <br>
Atmospheric Gas Absorption <br>
Atmospheric gas absoprtion in this model is approximated using the formula <br>
A<sub>atm</sub> = γ(f) * L<sub>eff</sub> / sin(θ) <br>
where: <br>
L<sub>eff</sub> = 8 km (assumed atmospher thickness) <br>
θ = elevation angle between the satellite& ground <br>
