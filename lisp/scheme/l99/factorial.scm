(define factorial
  (lambda (num)
    (cond
      ((eq? num 0) 1)
      (else (* num (factorial (- num 1)))))))

(print (factorial 5))
