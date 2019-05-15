(define a '(1 2 3 4 5 6))
(define b '())
(define c '(1 (2 3) 4 5 6))
(print (cons "a = " a))

(define atom? 
  (lambda (x)
    (cond ((null? x) #f)
          ((list? x) #f)
          (else      #t))))

(define lat?
  (lambda (x)
    (cond 
      ((null? x)      #t)
      ((atom? (car x)) (lat? (cdr x)))
      (else           #f))))

(print (lat? a))
(print (lat? b))
(print (lat? c))
