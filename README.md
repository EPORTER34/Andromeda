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
  - sat obrital mechanics <br>
    - tle parsing <br>
    - sgp4 propogation <br>
  - ground to sat comm <br>
    - link budget analysis <br>
    - path loss/SNR <br>
    - shadowing & atmospheric effects <br>
  - link everything together <br>
<br>

frontend: <br>
  - viewing pannels <br>
    - satellite numbers (with dropdown for orbital elements?) <br>
    - doppler effect <br>
    - link budget (with dropdowns for losses) <br>

<br>
  potentially add multithreading <br>
<br>
readme<br>
  actually document (assumptions made, features, design decisions) <br>

## Orbital Propagation <br>
### Position
Satellite orbits are assumed to be circular and are represented using four keplerian orbital elements detailed below: <br>
> Orbital Radius       (r) <br>
Inclination          (I) <br>
Ascending Longitude  (Ω) <br>
Anomaly              (v) <br>

Using these elements, position in ECI is then calculated using a series of rotations that result in the following equations: <br>
> x: r * (cos(Ω)cos(v) - sin(Ω)sin(v)cos(I)) <br>
y: r * (sin(Ω)cos(v) + cos(Ω)sin(v)cos(I)) <br>
z: r * sin(v)sin(I) <br>

Anomaly is calculated by using the angular velocity of the satellite & multiplying it by time. <br>
When the position is required in ECEF coordinates: <br>
> x<sub>ECEF</sub> = x<sub>ECI</sub>cos(θ) + y<sub>ECI</sub>sin(θ) <br>
y<sub>ECEF</sub> = -x<sub>ECI</sub>sin(θ) + y<sub>ECI</sub>cos(θ) <br>
z<sub>ECEF</sub> = z<sub>ECI</sub>

Where θ is calculated by multiplying the earth's angular velocity by simulation time
### Velocity
Velocity is calculated by taking the cross product between the orbital plane's normal vector, & the normalized position vector (ECI or ECEF), and then multiplying the result by the constant orbital velocity <br>
The orbital plane's normal vector is calculated using orbital elements as follows: <br>
> (sin(I)sin(Ω), -sin(I)sin(Ω), cos(I))

## Doppler Compensation <br>
nothing here yet <br>
## Losses <br>
### Atmospheric Gas Absorption <br>
Atmospheric gas absoprtion in this model is approximated using the formula: <br>
> A<sub>atm</sub> = γ(f) * L<sub>eff</sub> / sin(θ) <br>

where: <br>
f = carrier frequency in GHz <br>
L<sub>eff</sub> = 8 km (assumed atmosphere thickness) <br>
θ = elevation angle between the satellite & ground <br>
γ(f) = surface specific attenuation, which is given by the approximation: <br>
> γ(f) = .002 * f<sup>2</sup> / (f<sup>2</sup> + 25) + .0035 * f<sup>2</sup> / (f<sup>2</sup> + 9) <br>

Which comes from the standard γ function detailed in ITU-R P.676, where the mean global annual atmosphere is used. 
This model gives a rough approximation for frequencys < 40 GHz, but the water vapor resonance peak at ~22 GHz is not accurate. <br>
