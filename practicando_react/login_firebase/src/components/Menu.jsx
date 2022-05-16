import React, { useEffect, useState } from 'react'
import { Link, useHistory } from 'react-router-dom'
import { auth } from '../firebaseConfig'

const Menu = () => {
    const [user, setUser] = useState('')
    const history = useHistory()

    useEffect(() => {
        auth.onAuthStateChanged(user => {
            if (user) setUser(user.email)
        })
    }, [])

    const signOutUser = () => {
        auth.signOut()
        setUser('')
        history.push('/login')
    }

    return (
        <div>
            <nav className='navbar navbar-expand-lg navbar-dark bg-dark d-flex justify-content-between'>
                <ul className='navbar-nav mr-auto'>
                    <li className='nav-item ms-2'>
                        <Link className='nav-link' to='/'>Home</Link>
                    </li>
                    <li>
                        {
                            user ?
                            <span></span>
                            :
                            <Link className='nav-link' to='/login'>Login</Link>
                        }
                    </li>
                    <li>
                        <Link className='nav-link' to='/admin'>Admin</Link>
                    </li>
                </ul>
                {
                    user ?
                    <button 
                    onClick={signOutUser}
                    className='btn btn-danger me-5'
                    >Cerrar sesión</button>
                    :
                    <span></span>
                }
            </nav>
        </div>
    )
}

export default Menu