#ifndef VECTOR_H_
#define VECTOR_H_

class Vector3D
{
public:
	/**
	 * Constructs a vector where all of the components are 0.
	 */
	Vector3D();

	/**
	 * Constructs a vector with the specified values (X, Y, Z).
	 */
	Vector3D(double x, double y, double z);

	/**
	 * Returns the X component of the vector.
	 */
	double GetX() const;

	/**
	 * Returns the Y component of the vector.
	 */
	double GetY() const;

	/**
	 * Returns the Z component of the vector.
	 */
	double GetZ() const;

	/**
	 * Returns the dot product of this vector and the other specified
	 * vector.
	 */
	double DotProduct(const Vector3D &otherVector) const;

	/**
	 * Returns the length (magnitude) of the vector from the origin.
	 */
	double Length();

	/**
	 * Normalize the vector in-place to become a unit vector.
	 */
	void Normalize();

	/**
	 * Reverse the vector's direction in-place.
	 */
	void Reverse();

	/**
	 * Returns a new vector whose components are the sum of the
	 * components of the argument vectors.
	 */
	Vector3D operator+(const Vector3D &otherVector) const;

	/**
	 * Returns a new vector whose components are the difference of the
	 * components of the argument vectors.
	 */
	Vector3D operator-(const Vector3D &otherVector) const;

	/**
	 * Returns a new vector whose components have been scaled by the
	 * constant factor.
	 */
	Vector3D operator*(double scalingFactor) const;

	/**
	 * Returns a new vector whose components are the product of the
	 * components of the argument vectors.
	 */
	Vector3D operator*(const Vector3D &otherVector) const;

private:
	double x;
	double y;
	double z;
};

/**
 * This allows us to multiply with the scaling factor on the left,
 * ex: "2.5 * vector".  Otherwise we could only multiply with the
 * scaling factor on the right.
 */
Vector3D operator*(double scalingFactor, const Vector3D &vector);

#endif
