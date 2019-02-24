Recall from theory, we know that there are three points here:

		1.Construct a matrix based on two exists matrices
		2.Show a point of p, p', where p' = Cp
		3.Get perspective project of p'

So in camera.c, we have these functions:

camera.c:
	dmatrix_t *build_camera_matrix(dmatrix_t *E, dmatrix_t *G);
		Build a camera matrix based on two exist matrices.

	dmatrix_t *perspective_projection(dmatrix_t *P);
		Get a perspective matrix.


	main:
		make e /* The centre of projection for the camera */
		make g  /* Point gazed at by camera */
		C = camera(e,g)

		So we first make two point e,g then based on this, we make C.

		make p /* as point */
		Print C*p //P multiplied with camera matrix
		Print perspective_projection(C*p) //p after prespective projection

matrix.h:

	Firstly, let's find how to make a point or matrix:
	//one way to do it:	
	dmatrix_t test;
    dmat_alloc(&test,4,1); //notice: every time call a matrix you must use &.
    test.m[1][1] = 3.3 //notice, the index starts at 1;
    delete_dmatrix(&test);

    //recommend
    dmatrix_t *P; 
    P = (dmatrix_t *)malloc(sizeof(dmatrix_t));//difference one
    dmat_alloc(P,4,4) ;//initialization
    P = dmat_init(P,3.0);//initialization
    write_dmatrix(P);//print
    test->m[1][1] = 1.0;//difference two
    delete_dmatrix(test);//delete


	dmatrix:
		l: line
		c: column
		m: a 2d matrix

	void write_dmatrix(dmatrix_t *M); //print a matrix

	double **dmatrix(int nrl, int nrh, int ncl, int nch);
	//DON'T CARE: no direct access

	void free_dmatrix(double **m, int nrl, int nrh, int ncl, int nch);
	//DON'T CARE: no direct access

	void dmat_alloc(dmatrix_t *A, int l, int c);
	//l = line, the raw; c = column;

	dmatrix_t *dmat_duplicate(dmatrix_t *A);
	//copy

	dmatrix_t *dmat_init(dmatrix_t *A, double a);
	//initial the matrix with number a;

	dmatrix_t *dmat_init_2(dmatrix_t *A);
	//initial the matrix as "1234; 1234; 1234; 1234:"

	dmatrix_t *dmat_identity(dmatrix_t *A);
	//identity it. 

	dmatrix_t *dmat_scalar_mult(dmatrix_t *A, double a);
	//scalar it

	dmatrix_t *dmat_mult(dmatrix_t *A, dmatrix_t *B);
	//multiplication

	dmatrix_t *dmat_add(dmatrix_t *A, dmatrix_t *B);
	//addition

	dmatrix_t *dmat_sub(dmatrix_t *A, dmatrix_t *B);
	//sub

	double dmat_norm(dmatrix_t *A);
	//calculate norm of a vector. NORM = LENGTH

	dmatrix_t *dmat_normalize(dmatrix_t *A);
	//vector p -> unit vector. That is p/norm(p)

	dmatrix_t *dmat_transpose(dmatrix_t *A);
	//Transpose

	double ddot_product(dmatrix_t *A, dmatrix_t *B);
	//Dot product

	dmatrix_t *cross_product_matrix(dmatrix_t *A, dmatrix_t *B)
	//A intermediate way to get cross product.
	//e.g. a = 1 2 3; b = 4, 5, 6; then the product of this function is, 1 1 1; 1 2 3; 4 5 6

	dmatrix_t *dcross_product(dmatrix_t *A, dmatrix_t *B) 
	//Cross product. the input vector must be 1*3


	dmatrix_t *sub_matrix(dmatrix_t *A, int r, int c);
	//Get the line r, the column c out, making up a new one.

	double determinant(dmatrix_t *A);
	//determinant

	dmatrix_t *dmat_inverse(dmatrix_t *A);
	//Inverse matrix

	dmatrix_t *to_homogeneous(dmatrix_t *A, double l);
	//Change the rightest-last element into l, and the rest of last line and column into 0.

	dmatrix_t *from_homogeneous(dmatrix_t *A);
	//Change a m*n matrix into m-1*n-1







