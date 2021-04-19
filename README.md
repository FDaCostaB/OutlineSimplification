# OutlineSimplification
A simplification of a given image outlines using segment or bezier curve.

Input : A PBM format image

Output : EPS format image

limitDistance  : Maximum distance in pixel between the simplificated outline and the original one

# Segment / Bezier (degree 1)

'./test_simplif-contours image_input resultat_file limitDistance' from simplifSegments

# Bezier (degree 2)

'./test_simplif-bezier2 image_input resultat_file limitDistance' from simplifBezier2

# Bezier (degree 3)

'./test_simplif-bezier3 image_input resultat_file limitDistance' from simplifBezier3
