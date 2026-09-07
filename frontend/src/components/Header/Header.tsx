import mainLogo from "./assets/logo.png"
import simintechLogo from "./assets/logo-1.png"
import simintechLogoHover from "./assets/logo-1h.png"
import dassaultLogo from "./assets/logo-2.png"
import dassaultLogoHover from "./assets/logo-2h.png"
import lcmsLogo from "./assets/logo-3.png"
import lcmsLogoHover from "./assets/logo-3h.png"
import styles from "./Header.module.css"

type NavigationItem = {
	href: string;
	logo: string;
	hoverLogo: string;
	alt: string;
}

const navigationItems: NavigationItem[] = [
	{
		href: "#simintech",
		logo: simintechLogo,
		hoverLogo: simintechLogoHover,
		alt: "simintech",
	},
	{
		href: "#bsexalead",
		logo: dassaultLogo,
		hoverLogo: dassaultLogoHover,
		alt: "bsexalead",
	},
	{
		href: "#lcms",
		logo: lcmsLogo,
		hoverLogo: lcmsLogoHover,
		alt: "lcms",
	}
]

function Header() {
	return(
		<header className={styles.header}>
			<a href="#main" className={styles.brand}>
				<img src={mainLogo} alt="3VServices" />
			</a>
				<nav aria-label="Основная навигация">
					<ul className={styles.navigationList}>
						{
							navigationItems.map((navigationItem) => (
								<li key={navigationItem.href}>
									<a href={navigationItem.href} className={styles.productLink}>
										<img src={navigationItem.logo} alt={navigationItem.alt} className={styles.logo} />
										<img src={navigationItem.hoverLogo} alt="" className={styles.hoverLogo} />
									</a>
								</li>
							))
						}
						<li>
							<a href="#contacts" className={styles.contactsLink}>
								Контакты
							</a>
						</li>
					</ul>
				</nav>
		</header>
	);
}

export default Header;