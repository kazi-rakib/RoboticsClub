# Earthquake Detector Science Fair Project

## Project Title
**"Testing Earthquake-Resistant Building Designs Using an Arduino Vibration Detector"**

## Hypothesis
Buildings with cross-bracing and damping systems will reduce vibration magnitude by at least 30% compared to unprotected structures when subjected to simulated earthquake forces.

## Materials Needed

### Electronics
- Arduino Uno ($8)
- ADXL345 Accelerometer Module ($5)
- Buzzer ($1)
- 3 LEDs - green, yellow, red ($1)
- 3 × 220Ω resistors ($1)
- Breadboard ($2)
- Jumper wires ($2)
- USB cable (included with Arduino)

### Building Materials
- Popsicle sticks (100 pack, $3)
- Hot glue gun and glue sticks ($5)
- Cardboard pieces
- Small weights (washers, coins)
- Rubber bands
- Foam padding pieces
- Wooden base board (12" × 12")

**Total Cost: ~$28**

## Experimental Design

### Part 1: Sensor Calibration
1. Test the sensor's sensitivity by creating controlled vibrations
2. Drop weights from different heights (10cm, 20cm, 30cm)
3. Record vibration magnitude for each
4. Create a calibration curve

### Part 2: Building Model Testing

**Create 5 different building models (each 6-8 inches tall):**

1. **Control Model**: Simple vertical stick structure, no reinforcement
2. **Cross-Braced Model**: Diagonal supports forming X-patterns
3. **Base-Isolated Model**: Structure sitting on rubber pads
4. **Damped Model**: Suspended weight at top (tuned mass damper)
5. **Combined Model**: Cross-bracing + base isolation

### Part 3: Testing Procedure

**For each building model:**

1. Place model on the wooden base board
2. Attach Arduino detector to the top of the model
3. Create standardized vibrations by:
   - Tapping the base with consistent force (use a pendulum)
   - Or using a small motor with offset weight
   - Or manually shaking the board following a pattern
4. Run 5 trials for each model
5. Record for each trial:
   - Peak vibration magnitude
   - Duration of shaking
   - Number of "aftershocks" detected
   - Any structural damage

## Data Collection

### Variables to Measure
- **Independent Variable**: Building design type
- **Dependent Variables**: 
  - Peak acceleration (m/s²)
  - Vibration duration (milliseconds)
  - Structural integrity (visual inspection)
- **Controlled Variables**: 
  - Vibration source intensity
  - Building height
  - Building mass
  - Number of materials used

### Data Table Template

| Model Type | Trial | Peak Magnitude (m/s²) | Duration (ms) | Damage? |
|------------|-------|----------------------|---------------|---------|
| Control    | 1     |                      |               |         |
| Control    | 2     |                      |               |         |
| ...        | ...   |                      |               |         |

## Analysis

1. **Calculate averages** for each building type
2. **Create graphs**:
   - Bar chart: Average peak magnitude by building type
   - Line graph: Vibration over time for each model
   - Comparison chart: Vibration reduction percentage
3. **Statistical analysis**: Calculate standard deviation and percent reduction from control

## Display Board Sections

### Title & Introduction
- Explain why earthquake-resistant buildings matter
- Real-world examples (Japan, California buildings)

### Hypothesis & Variables
- Clear statement of what you're testing
- List independent, dependent, controlled variables

### Materials & Methods
- Photos of your Arduino setup
- Diagrams of each building design
- Step-by-step testing procedure

### Results
- Data tables with all measurements
- Graphs showing comparisons
- Photos of models before/after testing

### Conclusion
- Which design was most effective?
- Did results support your hypothesis?
- Real-world applications
- Limitations and future improvements

## Tips for Success

1. **Document everything**: Take photos and videos during testing
2. **Repeat trials**: More data = more reliable results
3. **Be consistent**: Use exact same vibration method each time
4. **Save your data**: Export Serial Monitor data to Excel for graphing
5. **Safety**: Use hot glue gun with adult supervision

## Extensions & Improvements

- Test different building heights
- Vary the mass/weight of buildings
- Test different vibration frequencies (earthquakes vary)
- Compare to real Richter scale equivalents
- Add LCD screen to display real-time readings
- Build a shake table for more realistic testing

## Science Fair Presentation Tips

- Bring your working Arduino detector to demonstrate
- Have at least one intact model on display
- Create a short video showing dramatic testing moments
- Prepare to explain how the accelerometer works
- Be ready to discuss real earthquake engineering principles