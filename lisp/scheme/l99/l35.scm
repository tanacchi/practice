(define (prime-factors num)
  (define (prime-factors-aux num base result)
    (cond
      ((is-prime num) (cons num result))
      ((and (zero? (modulo num base)) (is-prime base))
       (prime-factors-aux (/ num base) 2 (cons base result)))
      (else (prime-factors-aux num (+ base 1) result))))
  (reverse (prime-factors-aux num 2 '())))
