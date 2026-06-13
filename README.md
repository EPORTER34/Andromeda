# Andromeda
3d simulator for a satellite network the plots satellite orbits & simulates communications between the ground and sattelites
will contain a preset of a LEO, MEO, & GEO sat network & the option to custom load a network <br>
Assumptions: <br>
circular satellite orbits <br>
multipath mostly negligeble <br>
ignoring drag & any other orbital drift <br>
assuming earth is a sphere of radius 6378 km <br>

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
  pan left/right on OrbitalView <br>
  viewing pannels <br>
    satellite numbers (with dropdown for orbital elements?) <br>
    doppler effect <br>
    link budget (with dropdowns for losses) <br>

<br>
  potentially add multithreading <br>
<br>
readme<br>
  actually document (assumptions made, features, design decisions) <br>