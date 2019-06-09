(define factorial
  (lambda (num)
    (cond
      ((eq? num 0) 1)
      (else (* num (factorial (sub1 num)))))))

(define (factorial-tr num)
  (define (factorial-tr-aux count result)
    (cond
      ((zero? count) result)
      (else (factorial-tr-aux (sub1 count) (* result count)))))
  (factorial-tr-aux num 1))


(time (for-each factorial (range 1000)))
(time (for-each factorial-tr (range 1000)))
